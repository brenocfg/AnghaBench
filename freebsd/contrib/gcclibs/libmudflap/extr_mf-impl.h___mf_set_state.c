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
typedef  enum __mf_state_enum { ____Placeholder___mf_state_enum } __mf_state_enum ;

/* Variables and functions */
 int __mf_state_1 ; 

__attribute__((used)) static inline void __mf_set_state (enum __mf_state_enum s)
{
  __mf_state_1 = s;
}