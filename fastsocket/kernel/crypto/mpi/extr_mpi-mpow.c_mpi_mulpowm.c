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
 int /*<<< orphan*/  BUG () ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int build_index (int /*<<< orphan*/ **,int,int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpi_alloc (scalar_t__) ; 
 int /*<<< orphan*/ * mpi_alloc_set_ui (int) ; 
 scalar_t__ mpi_copy (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpi_free (int /*<<< orphan*/ *) ; 
 int mpi_get_nbits (int /*<<< orphan*/ *) ; 
 scalar_t__ mpi_get_nlimbs (int /*<<< orphan*/ *) ; 
 scalar_t__ mpi_mulm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mpi_set_ui (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printk (char*) ; 

int
mpi_mulpowm( MPI res, MPI *basearray, MPI *exparray, MPI m)
{
	int rc = -ENOMEM;
	int k;	/* number of elements */
	int t;	/* bit size of largest exponent */
	int i, j, idx;
	MPI *G = NULL;	/* table with precomputed values of size 2^k */
	MPI tmp = NULL;

	for(k=0; basearray[k]; k++ )
		;
	if (!k) { printk("mpi_mulpowm: assert(k) failed\n"); BUG(); }
	for(t=0, i=0; (tmp=exparray[i]); i++ ) {
		j = mpi_get_nbits(tmp);
		if( j > t )
			t = j;
	}
	if (i!=k) { printk("mpi_mulpowm: assert(i==k) failed\n"); BUG(); }
	if (!t)	  { printk("mpi_mulpowm: assert(t) failed\n"); BUG(); }
	if (k>=10) { printk("mpi_mulpowm: assert(k<10) failed\n"); BUG(); }

	G = kzalloc( (1<<k) * sizeof *G, GFP_KERNEL );
	if (!G) goto nomem;

	/* and calculate */
	tmp =  mpi_alloc( mpi_get_nlimbs(m)+1 ); if (!tmp) goto nomem;
	if (mpi_set_ui( res, 1 ) < 0) goto nomem;
	for(i = 1; i <= t; i++ ) {
		if (mpi_mulm(tmp, res, res, m ) < 0) goto nomem;
		idx = build_index( exparray, k, i, t );
		if (!(idx >= 0 && idx < (1<<k))) {
			printk("mpi_mulpowm: assert(idx >= 0 && idx < (1<<k)) failed\n");
			BUG();
		}
		if( !G[idx] ) {
			if( !idx ) {
				G[0] = mpi_alloc_set_ui( 1 );
				if (!G[0]) goto nomem;
			}
			else {
				for(j=0; j < k; j++ ) {
					if( (idx & (1<<j) ) ) {
						if( !G[idx] ) {
							if (mpi_copy( &G[idx], basearray[j] ) < 0)
								goto nomem;
						}
						else {
							if (mpi_mulm(G[idx],G[idx],basearray[j],m) < 0)
								goto nomem;
						}
					}
				}
				if( !G[idx] ) {
					G[idx] = mpi_alloc(0);
					if (!G[idx]) goto nomem;
				}
			}
		}
		if (mpi_mulm(res, tmp, G[idx], m ) < 0) goto nomem;
	}

	rc = 0;
 nomem:
	/* cleanup */
	mpi_free(tmp);
	for(i=0; i < (1<<k); i++ )
		mpi_free(G[i]);
	kfree(G);
	return rc;
}