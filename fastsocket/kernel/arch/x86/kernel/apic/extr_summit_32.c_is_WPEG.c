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
struct rio_detail {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AltWPEG ; 
 scalar_t__ CompatWPEG ; 
 scalar_t__ LookOutAWPEG ; 
 scalar_t__ LookOutBWPEG ; 

__attribute__((used)) static inline int is_WPEG(struct rio_detail *rio){
	return (rio->type == CompatWPEG || rio->type == AltWPEG ||
		rio->type == LookOutAWPEG || rio->type == LookOutBWPEG);
}