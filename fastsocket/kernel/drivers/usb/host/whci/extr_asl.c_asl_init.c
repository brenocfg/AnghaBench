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
struct whc_qset {int dummy; } ;
struct whc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  asl_qset_insert (struct whc*,struct whc_qset*) ; 
 int /*<<< orphan*/  asl_qset_insert_begin (struct whc*,struct whc_qset*) ; 
 struct whc_qset* qset_alloc (struct whc*,int /*<<< orphan*/ ) ; 

int asl_init(struct whc *whc)
{
	struct whc_qset *qset;

	qset = qset_alloc(whc, GFP_KERNEL);
	if (qset == NULL)
		return -ENOMEM;

	asl_qset_insert_begin(whc, qset);
	asl_qset_insert(whc, qset);

	return 0;
}