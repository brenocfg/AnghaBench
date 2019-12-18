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
struct itbl_entry {int dummy; } ;
typedef  size_t e_type ;
typedef  size_t e_processor ;

/* Variables and functions */
 struct itbl_entry*** entries ; 

__attribute__((used)) static struct itbl_entry **
get_entries (e_processor processor, e_type type)
{
  return &entries[processor][type];
}