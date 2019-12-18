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
struct radix_node {int rn_flags; struct radix_mask* rn_mklist; int /*<<< orphan*/  rn_mask; int /*<<< orphan*/  rn_bit; } ;
struct radix_mask {int rm_flags; struct radix_mask* rm_mklist; int /*<<< orphan*/  rm_mask; struct radix_node* rm_leaf; int /*<<< orphan*/  rm_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  Bzero (struct radix_mask*,int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  MKGet (struct radix_mask*) ; 
 int RNF_NORMAL ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct radix_mask *
rn_new_radix_mask(struct radix_node *tt, struct radix_mask *next)
{
	struct radix_mask *m;

	MKGet(m);
	if (m == 0) {
		log(LOG_ERR, "Mask for route not entered\n");
		return (NULL);
	}
	Bzero(m, sizeof *m);
	m->rm_bit = tt->rn_bit;
	m->rm_flags = tt->rn_flags;
	if (tt->rn_flags & RNF_NORMAL)
		m->rm_leaf = tt;
	else
		m->rm_mask = tt->rn_mask;
	m->rm_mklist = next;
	tt->rn_mklist = m;
	return m;
}