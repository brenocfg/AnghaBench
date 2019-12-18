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
struct qdio_initialize {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int qdio_allocate (struct qdio_initialize*) ; 
 int qdio_establish (struct qdio_initialize*) ; 
 int /*<<< orphan*/  qdio_free (int /*<<< orphan*/ ) ; 

int qdio_initialize(struct qdio_initialize *init_data)
{
	int rc;

	rc = qdio_allocate(init_data);
	if (rc)
		return rc;

	rc = qdio_establish(init_data);
	if (rc)
		qdio_free(init_data->cdev);
	return rc;
}