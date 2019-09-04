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
typedef  int /*<<< orphan*/  InterplayACMContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 

__attribute__((used)) static int bad(InterplayACMContext *s, unsigned ind, unsigned col)
{
    return AVERROR_INVALIDDATA;
}