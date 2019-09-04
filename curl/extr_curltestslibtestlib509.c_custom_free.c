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
typedef  int /*<<< orphan*/  free ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 
 int seen_free ; 
 scalar_t__ seen_realloc ; 

void custom_free(void *ptr)
{
  if(!seen_free && seen_realloc) {
    printf("seen custom_free()\n");
    seen_free = 1;
  }
  (free)(ptr);
}