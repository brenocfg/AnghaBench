#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/ * MPI ;

/* Variables and functions */
 int EINVAL ; 
 int EKEYREJECTED ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * mpi_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ mpi_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mpi_cmp_ui (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mpi_fdiv_r (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpi_get_nlimbs (int /*<<< orphan*/ *) ; 
 scalar_t__ mpi_invm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mpi_mulm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mpi_mulpowm (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*) ; 

int DSA_verify(const MPI datahash, const MPI sig[], const MPI pkey[])
{
	MPI p, q, g, y, r, s;
	MPI w = NULL, u1 = NULL, u2 = NULL, v = NULL;
	MPI base[3];
	MPI exp[3];
	int rc;

	if (!datahash ||
	    !sig[0] || !sig[1] ||
	    !pkey[0] || !pkey[1] || !pkey[2] || !pkey[3])
		return -EINVAL;

	p = pkey[0];	/* prime */
	q = pkey[1];	/* group order */
	g = pkey[2];	/* group generator */
	y = pkey[3];	/* g^x mod p */
	r = sig[0];
	s = sig[1];

	if (!(mpi_cmp_ui(r, 0) > 0 && mpi_cmp(r, q) < 0)) {
		printk("DSA_verify assertion failed [0 < r < q]\n");
		return -EKEYREJECTED;
	}

	if (!(mpi_cmp_ui(s, 0) > 0 && mpi_cmp(s, q) < 0)) {
		printk("DSA_verify assertion failed [0 < s < q]\n");
		return -EKEYREJECTED;
	}

	rc = -ENOMEM;
	w  = mpi_alloc(mpi_get_nlimbs(q)); if (!w ) goto cleanup;
	u1 = mpi_alloc(mpi_get_nlimbs(q)); if (!u1) goto cleanup;
	u2 = mpi_alloc(mpi_get_nlimbs(q)); if (!u2) goto cleanup;
	v  = mpi_alloc(mpi_get_nlimbs(p)); if (!v ) goto cleanup;

	/* w = s^(-1) mod q */
	if (mpi_invm(w, s, q) < 0)
		goto cleanup;

	/* u1 = (datahash * w) mod q */
	if (mpi_mulm(u1, datahash, w, q) < 0)
		goto cleanup;

	/* u2 = r * w mod q  */
	if (mpi_mulm(u2, r, w, q) < 0)
		goto cleanup;

	/* v =  g^u1 * y^u2 mod p mod q */
	base[0] = g;	exp[0] = u1;
	base[1] = y;	exp[1] = u2;
	base[2] = NULL;	exp[2] = NULL;

	if (mpi_mulpowm(v, base, exp, p) < 0)
		goto cleanup;

	if (mpi_fdiv_r(v, v, q) < 0)
		goto cleanup;

	rc = (mpi_cmp(v, r) == 0) ? 0 : -EKEYREJECTED;

cleanup:
	mpi_free(w);
	mpi_free(u1);
	mpi_free(u2);
	mpi_free(v);
	return rc;
}