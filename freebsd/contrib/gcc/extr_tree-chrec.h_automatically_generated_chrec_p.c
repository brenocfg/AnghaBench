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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ chrec_dont_know ; 
 scalar_t__ chrec_known ; 
 scalar_t__ chrec_not_analyzed_yet ; 

__attribute__((used)) static inline bool
automatically_generated_chrec_p (tree chrec)
{
  return (chrec == chrec_not_analyzed_yet 
	  || chrec == chrec_dont_know
	  || chrec == chrec_known);
}