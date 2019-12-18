#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct httpd_req_aux {char* scratch; unsigned int req_hdrs_count; } ;
struct TYPE_4__ {struct httpd_req_aux* aux; } ;
typedef  TYPE_1__ httpd_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  httpd_valid_req (TYPE_1__*) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

size_t httpd_req_get_hdr_value_len(httpd_req_t *r, const char *field)
{
    if (r == NULL || field == NULL) {
        return 0;
    }

    if (!httpd_valid_req(r)) {
        return 0;
    }

    struct httpd_req_aux *ra = r->aux;
    const char   *hdr_ptr = ra->scratch;         /*!< Request headers are kept in scratch buffer */
    unsigned      count   = ra->req_hdrs_count;  /*!< Count set during parsing  */

    while (count--) {
        /* Search for the ':' character. Else, it would mean
         * that the field is invalid
         */
        const char *val_ptr = strchr(hdr_ptr, ':');
        if (!val_ptr) {
            break;
        }

        /* If the field, does not match, continue searching.
         * Compare lengths first as field from header is not
         * null terminated (has ':' in the end).
         */
        if ((val_ptr - hdr_ptr != strlen(field)) ||
            (strncasecmp(hdr_ptr, field, strlen(field)))) {
            if (count) {
                /* Jump to end of header field-value string */
                hdr_ptr = 1 + strchr(hdr_ptr, '\0');

                /* Skip all null characters (with which the line
                 * terminators had been overwritten) */
                while (*hdr_ptr == '\0') {
                    hdr_ptr++;
                }
            }
            continue;
        }

        /* Skip ':' */
        val_ptr++;

        /* Skip preceding space */
        while ((*val_ptr != '\0') && (*val_ptr == ' ')) {
            val_ptr++;
        }
        return strlen(val_ptr);
    }
    return 0;
}