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
typedef  int cap_rights_t ;

/* Variables and functions */

inline bool cap_rights_contains(const cap_rights_t *big, const cap_rights_t *little) {
  return ((*big) & (*little)) == (*little);
}