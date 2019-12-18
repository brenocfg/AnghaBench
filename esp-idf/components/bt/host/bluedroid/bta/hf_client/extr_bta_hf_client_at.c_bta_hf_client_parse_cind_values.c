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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  AT_CHECK_RN (char*) ; 
 int /*<<< orphan*/  bta_hf_client_handle_cind_value (scalar_t__,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static char *bta_hf_client_parse_cind_values(char *buffer)
{
    /* value and its position */
    UINT16 index = 0;
    UINT32 value = 0;

    int offset;
    int res;

    while ((res = sscanf(buffer, "%u%n", &value, &offset)) > 0) {
        /* decides if its valid index and value, if yes stores it */
        bta_hf_client_handle_cind_value(index, value);

        buffer += offset;

        /* check if more values are present */
        if (*buffer != ',') {
            break;
        }

        index++;
        buffer++;
    }

    if (res > 0) {
        AT_CHECK_RN(buffer);
        return buffer;
    }

    return NULL;
}