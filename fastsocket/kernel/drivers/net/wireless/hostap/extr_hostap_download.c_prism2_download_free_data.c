#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct prism2_download_data {int num_areas; TYPE_1__* data; } ;
struct TYPE_2__ {struct prism2_download_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct prism2_download_data*) ; 

__attribute__((used)) static void prism2_download_free_data(struct prism2_download_data *dl)
{
	int i;

	if (dl == NULL)
		return;

	for (i = 0; i < dl->num_areas; i++)
		kfree(dl->data[i].data);
	kfree(dl);
}