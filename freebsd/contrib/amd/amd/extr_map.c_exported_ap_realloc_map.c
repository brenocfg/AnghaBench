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
typedef  int /*<<< orphan*/  voidp ;
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 int /*<<< orphan*/ ** exported_ap ; 
 int exported_ap_size ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xrealloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
exported_ap_realloc_map(int nsize)
{
  /*
   * this shouldn't happen, but...
   */
  if (nsize < 0 || nsize == exported_ap_size)
    return 0;

  exported_ap = (am_node **) xrealloc((voidp) exported_ap, nsize * sizeof(am_node *));

  if (nsize > exported_ap_size)
    memset((char *) (exported_ap + exported_ap_size), 0,
	  (nsize - exported_ap_size) * sizeof(am_node *));
  exported_ap_size = nsize;

  return 1;
}