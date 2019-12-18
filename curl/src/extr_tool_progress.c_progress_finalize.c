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
struct per_transfer {scalar_t__ ulnow; scalar_t__ dlnow; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_dlalready ; 
 int /*<<< orphan*/  all_ulalready ; 

void progress_finalize(struct per_transfer *per)
{
  /* get the numbers before this transfer goes away */
  all_dlalready += per->dlnow;
  all_ulalready += per->ulnow;
}