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

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (char*) ; 
 char* dasd_parse_keyword (char*) ; 
 char* dasd_parse_range (char*) ; 

__attribute__((used)) static char *
dasd_parse_next_element( char *parsestring ) {
	char * residual_str;
	residual_str = dasd_parse_keyword(parsestring);
	if (!IS_ERR(residual_str))
		return residual_str;
	residual_str = dasd_parse_range(parsestring);
	return residual_str;
}