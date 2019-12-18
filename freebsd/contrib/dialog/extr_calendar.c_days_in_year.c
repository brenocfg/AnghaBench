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
struct tm {scalar_t__ tm_year; } ;

/* Variables and functions */
 int days_per_year (scalar_t__) ; 

__attribute__((used)) static int
days_in_year(struct tm *current, int offset /* -1, 0, 1 */ )
{
    return days_per_year(current->tm_year + 1900 + offset);
}