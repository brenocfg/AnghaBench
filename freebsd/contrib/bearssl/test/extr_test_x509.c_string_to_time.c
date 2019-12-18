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
typedef  int uint32_t ;

/* Variables and functions */
 int month_length (int,int) ; 
 scalar_t__ parse_choice (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ parse_dec (char const*,int,int*) ; 

__attribute__((used)) static int
string_to_time(const char *s, uint32_t *days, uint32_t *seconds)
{
	int year, month, day, hour, minute, second;
	int day_of_year, leaps, i;

	if (parse_dec(s, 4, &year) < 0) {
		return -1;
	}
	s += 4;
	if (parse_choice(s ++, "-:/ ") < 0) {
		return -1;
	}
	if (parse_dec(s, 2, &month) < 0) {
		return -1;
	}
	s += 2;
	if (parse_choice(s ++, "-:/ ") < 0) {
		return -1;
	}
	if (parse_dec(s, 2, &day) < 0) {
		return -1;
	}
	s += 2;
	if (parse_choice(s ++, " T") < 0) {
		return -1;
	}
	if (parse_dec(s, 2, &hour) < 0) {
		return -1;
	}
	s += 2;
	if (parse_choice(s ++, "-:/ ") < 0) {
		return -1;
	}
	if (parse_dec(s, 2, &minute) < 0) {
		return -1;
	}
	s += 2;
	if (parse_choice(s ++, "-:/ ") < 0) {
		return -1;
	}
	if (parse_dec(s, 2, &second) < 0) {
		return -1;
	}
	s += 2;
	if (*s == '.') {
		while (*s && *s >= '0' && *s <= '9') {
			s ++;
		}
	}
	if (*s) {
		if (*s ++ != 'Z') {
			return -1;
		}
		if (*s) {
			return -1;
		}
	}

	if (month < 1 || month > 12) {
		return -1;
	}
	day_of_year = 0;
	for (i = 1; i < month; i ++) {
		day_of_year += month_length(year, i);
	}
	if (day < 1 || day > month_length(year, month)) {
		return -1;
	}
	day_of_year += (day - 1);
	leaps = (year + 3) / 4 - (year + 99) / 100 + (year + 399) / 400;

	if (hour > 23 || minute > 59 || second > 60) {
		return -1;
	}
	*days = (uint32_t)year * 365 + (uint32_t)leaps + day_of_year;
	*seconds = (uint32_t)hour * 3600 + minute * 60 + second;
	return 0;
}