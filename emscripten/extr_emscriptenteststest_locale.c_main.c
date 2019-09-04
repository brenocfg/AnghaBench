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
struct lconv {char* decimal_point; char* thousands_sep; char* grouping; char* int_curr_symbol; char* currency_symbol; char* mon_decimal_point; char* mon_thousands_sep; char* mon_grouping; char* positive_sign; char* negative_sign; } ;

/* Variables and functions */
 struct lconv* localeconv () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main()
{
    // Test basic functions from classic locale.
    struct lconv* locale = localeconv();

    printf("Testing locale information.\n");
    printf("Decimal point: %s\n", locale->decimal_point);
    printf("Thousands separator: %s\n", locale->thousands_sep);
    printf("Grouping: %s\n", locale->grouping);
    printf("International currency symbol: %s\n", locale->int_curr_symbol);
    printf("Currency symbol: %s\n", locale->currency_symbol);
    printf("Money decimal point: %s\n", locale->mon_decimal_point);
    printf("Money thousands separator: %s\n", locale->mon_thousands_sep);
    printf("Money Grouping: %s\n", locale->mon_grouping);
    printf("Positive sign: %s\n", locale->positive_sign);
    printf("Negative sign: %s\n", locale->negative_sign);
    
    // If no runtime errors, assume the test passed.
    printf("Locale tests passed.\n");
    return 0;
}