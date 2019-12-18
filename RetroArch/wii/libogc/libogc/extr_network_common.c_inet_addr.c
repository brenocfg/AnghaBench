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
typedef  int /*<<< orphan*/  u32_t ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_NONE ; 
 scalar_t__ inet_aton (char const*,struct in_addr*) ; 

u32_t inet_addr(const char *cp)
 {
     struct in_addr val;

     if (inet_aton(cp, &val)) {
         return (val.s_addr);
     }
     return (INADDR_NONE);
 }