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
struct peespi {int /*<<< orphan*/ * adapter; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct peespi* kzalloc (int,int /*<<< orphan*/ ) ; 

struct peespi *t1_espi_create(adapter_t *adapter)
{
	struct peespi *espi = kzalloc(sizeof(*espi), GFP_KERNEL);

	if (espi)
		espi->adapter = adapter;
	return espi;
}