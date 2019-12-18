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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_HTTPD_INVALID_REQ ; 
 int /*<<< orphan*/  ESP_ERR_HTTPD_RESULT_TRUNC ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  httpd_valid_req (TYPE_1__*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t const) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,int) ; 

esp_err_t httpd_req_get_hdr_value_str(httpd_req_t *r, const char *field, char *val, size_t val_size)
{
    if (r == NULL || field == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!httpd_valid_req(r)) {
        return ESP_ERR_HTTPD_INVALID_REQ;
    }

    struct httpd_req_aux *ra = r->aux;
    const char   *hdr_ptr = ra->scratch;         /*!< Request headers are kept in scratch buffer */
    unsigned     count    = ra->req_hdrs_count;  /*!< Count set during parsing  */
    const size_t buf_len  = val_size;

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

        /* Get the NULL terminated value and copy it to the caller's buffer. */
        strlcpy(val, val_ptr, buf_len);

        /* Update value length, including one byte for null */
        val_size = strlen(val_ptr) + 1;

        /* If buffer length is smaller than needed, return truncation error */
        if (buf_len < val_size) {
            return ESP_ERR_HTTPD_RESULT_TRUNC;
        }
        return ESP_OK;
    }
    return ESP_ERR_NOT_FOUND;
}