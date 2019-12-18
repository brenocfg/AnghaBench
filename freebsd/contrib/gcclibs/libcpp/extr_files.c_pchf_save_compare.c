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
struct pchf_entry {int dummy; } ;

/* Variables and functions */
 int memcmp (void const*,void const*,int) ; 

__attribute__((used)) static int
pchf_save_compare (const void *e1, const void *e2)
{
  return memcmp (e1, e2, sizeof (struct pchf_entry));
}