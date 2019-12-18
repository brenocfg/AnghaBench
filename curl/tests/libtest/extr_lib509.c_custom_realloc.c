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
typedef  void* realloc ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ seen_malloc ; 
 int seen_realloc ; 

void *custom_realloc(void *ptr, size_t size)
{
  if(!seen_realloc && seen_malloc) {
    printf("seen custom_realloc()\n");
    seen_realloc = 1;
  }
  return (realloc)(ptr, size);
}