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
struct pt1_adapter {int index; } ;
struct pt1 {struct pt1_adapter** adaps; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pt1_adapter*) ; 
 int PT1_NR_ADAPS ; 
 int PTR_ERR (struct pt1_adapter*) ; 
 struct pt1_adapter* pt1_alloc_adapter (struct pt1*) ; 
 int /*<<< orphan*/  pt1_free_adapter (struct pt1_adapter*) ; 

__attribute__((used)) static int pt1_init_adapters(struct pt1 *pt1)
{
	int i;
	struct pt1_adapter *adap;
	int ret;

	for (i = 0; i < PT1_NR_ADAPS; i++) {
		adap = pt1_alloc_adapter(pt1);
		if (IS_ERR(adap)) {
			ret = PTR_ERR(adap);
			goto err;
		}

		adap->index = i;
		pt1->adaps[i] = adap;
	}
	return 0;

err:
	while (i--)
		pt1_free_adapter(pt1->adaps[i]);

	return ret;
}