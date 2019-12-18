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
typedef  int /*<<< orphan*/  ogg_page ;

/* Variables and functions */
 int _lookup_serialno (long,long*,int) ; 
 long ogg_page_serialno (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _lookup_page_serialno(ogg_page *og, long *serialno_list, int n){
  long s = ogg_page_serialno(og);
  return _lookup_serialno(s,serialno_list,n);
}