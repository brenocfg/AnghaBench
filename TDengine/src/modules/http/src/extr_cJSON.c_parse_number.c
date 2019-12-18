#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t offset; int /*<<< orphan*/ * content; } ;
typedef  TYPE_1__ parse_buffer ;
typedef  int /*<<< orphan*/  number_c_string ;
typedef  double int64_t ;
typedef  int cJSON_bool ;
struct TYPE_8__ {double valuedouble; double valueint; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ cJSON ;

/* Variables and functions */
 double LLONG_MAX ; 
 double LLONG_MIN ; 
 int* buffer_at_offset (TYPE_1__* const) ; 
 int /*<<< orphan*/  cJSON_Number ; 
 scalar_t__ can_access_at_index (TYPE_1__* const,size_t) ; 
 unsigned char get_decimal_point () ; 
 double strtod (char const*,char**) ; 

__attribute__((used)) static cJSON_bool parse_number(cJSON * const item, parse_buffer * const input_buffer)
{
    double number = 0;
    unsigned char *after_end = NULL;
    unsigned char number_c_string[64];
    unsigned char decimal_point = get_decimal_point();
    size_t i = 0;

    if ((input_buffer == NULL) || (input_buffer->content == NULL))
    {
        return false;
    }

    /* copy the number into a temporary buffer and replace '.' with the decimal point
     * of the current locale (for strtod)
     * This also takes care of '\0' not necessarily being available for marking the end of the input */
    for (i = 0; (i < (sizeof(number_c_string) - 1)) && can_access_at_index(input_buffer, i); i++)
    {
        switch (buffer_at_offset(input_buffer)[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '+':
            case '-':
            case 'e':
            case 'E':
                number_c_string[i] = buffer_at_offset(input_buffer)[i];
                break;

            case '.':
                number_c_string[i] = decimal_point;
                break;

            default:
                goto loop_end;
        }
    }
loop_end:
    number_c_string[i] = '\0';

    number = strtod((const char*)number_c_string, (char**)&after_end);
    if (number_c_string == after_end)
    {
        return false; /* parse_error */
    }

    item->valuedouble = number;

    /* use saturation in case of overflow */
    if (number >= LLONG_MAX)
    {
        item->valueint = LLONG_MAX;
    }
    else if (number <= LLONG_MIN)
    {
        item->valueint = LLONG_MIN;
    }
    else
    {
        item->valueint = (int64_t)number;
    }

    item->type = cJSON_Number;

    input_buffer->offset += (size_t)(after_end - number_c_string);
    return true;
}