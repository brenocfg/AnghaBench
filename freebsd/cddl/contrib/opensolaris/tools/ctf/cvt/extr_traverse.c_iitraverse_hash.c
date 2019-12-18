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
typedef  int /*<<< orphan*/  tdtrav_data_t ;
typedef  int /*<<< orphan*/  tdtrav_cb_f ;
typedef  int /*<<< orphan*/  hash_t ;

/* Variables and functions */
 int hash_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iitraverse_td ; 
 int /*<<< orphan*/  tdtrav_init (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

int
iitraverse_hash(hash_t *iihash, int *vgenp, tdtrav_cb_f *firstops,
    tdtrav_cb_f *preops, tdtrav_cb_f *postops, void *private)
{
	tdtrav_data_t tdtd;

	tdtrav_init(&tdtd, vgenp, firstops, preops, postops, private);

	return (hash_iter(iihash, iitraverse_td, &tdtd));
}