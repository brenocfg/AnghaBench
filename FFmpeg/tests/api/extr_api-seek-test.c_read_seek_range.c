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
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ ERANGE ; 
 long LONG_MAX ; 
 long LONG_MIN ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ errno ; 
 int strlen (char const*) ; 
 long strtol (char const*,char**,int) ; 

__attribute__((used)) static long int read_seek_range(const char *string_with_number)
{
    long int number;
    char *end_of_string = NULL;
    number = strtol(string_with_number, &end_of_string, 10);
    if ((strlen(string_with_number) != end_of_string - string_with_number)  || (number < 0)) {
        av_log(NULL, AV_LOG_ERROR, "Incorrect input ranges of seeking\n");
        return -1;
    }
    else if ((number == LONG_MAX) || (number == LONG_MIN)) {
        if (errno == ERANGE) {
            av_log(NULL, AV_LOG_ERROR, "Incorrect input ranges of seeking\n");
            return -1;
        }
    }
    return number;
}