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
struct natt_status {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct natt_status*,int /*<<< orphan*/ ,int) ; 

bool natt_new(struct natt_status *status)
{
   memset(status, 0, sizeof(struct natt_status));
   return true;
}