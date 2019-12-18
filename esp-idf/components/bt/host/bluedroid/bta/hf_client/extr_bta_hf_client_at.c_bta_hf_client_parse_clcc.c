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
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  AT_CHECK_EVENT (char*,char*) ; 
 int /*<<< orphan*/  AT_CHECK_RN (char*) ; 
 int /*<<< orphan*/  bta_hf_client_handle_clcc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sscanf (char*,char*,char*,int*,...) ; 

__attribute__((used)) static char *bta_hf_client_parse_clcc(char *buffer)
{
    UINT16 idx, dir, status, mode, mpty;
    char numstr[33];     /* spec forces 32 chars, plus one for \0*/
    UINT16 type;
    int res;
    int offset;
    AT_CHECK_EVENT(buffer, "+CLCC:");

    res = sscanf(buffer, "%hu,%hu,%hu,%hu,%hu%n",
                 &idx, &dir, &status, &mode, &mpty, &offset);
    if (res < 5) {
        return NULL;
    }

    buffer += offset;

    /* check optional part */
    if (*buffer == ',') {
        int res2;

        res2 = sscanf(buffer, ",\"%32[^\"]\",%hu%n", numstr, &type, &offset);
        if (res2 < 0) {
            return NULL;
        }

        if (res2 == 0) {
            res2 = sscanf(buffer, ",\"\",%hu%n", &type, &offset);
            if (res < 0) {
                return NULL;
            }

            /* numstr is not matched in second attempt, correct this */
            res2++;
            numstr[0] = '\0';
        }

        if (res2 < 2) {
            return NULL;
        }

        res += res2;
        buffer += offset;
    }

    AT_CHECK_RN(buffer);

    if (res > 6) {
        /* we also have last two optional parameters */
        bta_hf_client_handle_clcc(idx, dir, status, mode, mpty, numstr, type);
    } else {
        /* we didn't get the last two parameters */
        bta_hf_client_handle_clcc(idx, dir, status, mode, mpty, NULL, 0);
    }

    return buffer;
}