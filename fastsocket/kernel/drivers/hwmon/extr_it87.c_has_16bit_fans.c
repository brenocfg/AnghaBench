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
struct it87_data {scalar_t__ type; int revision; } ;

/* Variables and functions */
 scalar_t__ it87 ; 
 scalar_t__ it8712 ; 
 scalar_t__ it8716 ; 
 scalar_t__ it8718 ; 
 scalar_t__ it8720 ; 

__attribute__((used)) static inline int has_16bit_fans(const struct it87_data *data)
{
	/* IT8705F Datasheet 0.4.1, 3h == Version G.
	   IT8712F Datasheet 0.9.1, section 8.3.5 indicates 8h == Version J.
	   These are the first revisions with 16bit tachometer support. */
	return (data->type == it87 && data->revision >= 0x03)
	    || (data->type == it8712 && data->revision >= 0x08)
	    || data->type == it8716
	    || data->type == it8718
	    || data->type == it8720;
}