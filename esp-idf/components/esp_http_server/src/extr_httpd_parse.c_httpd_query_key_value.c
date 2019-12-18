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
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_HTTPD_RESULT_TRUNC ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  LOG_FMT (char*) ; 
 int /*<<< orphan*/  MIN (size_t,size_t const) ; 
 int /*<<< orphan*/  TAG ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 scalar_t__ strncasecmp (char const*,char const*,size_t) ; 

esp_err_t httpd_query_key_value(const char *qry_str, const char *key, char *val, size_t val_size)
{
    if (qry_str == NULL || key == NULL || val == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    const char   *qry_ptr = qry_str;
    const size_t  buf_len = val_size;

    while (strlen(qry_ptr)) {
        /* Search for the '=' character. Else, it would mean
         * that the parameter is invalid */
        const char *val_ptr = strchr(qry_ptr, '=');
        if (!val_ptr) {
            break;
        }
        size_t offset = val_ptr - qry_ptr;

        /* If the key, does not match, continue searching.
         * Compare lengths first as key from url is not
         * null terminated (has '=' in the end) */
        if ((offset != strlen(key)) ||
            (strncasecmp(qry_ptr, key, offset))) {
            /* Get the name=val string. Multiple name=value pairs
             * are separated by '&' */
            qry_ptr = strchr(val_ptr, '&');
            if (!qry_ptr) {
                break;
            }
            qry_ptr++;
            continue;
        }

        /* Locate start of next query */
        qry_ptr = strchr(++val_ptr, '&');
        /* Or this could be the last query, in which
         * case get to the end of query string */
        if (!qry_ptr) {
            qry_ptr = val_ptr + strlen(val_ptr);
        }

        /* Update value length, including one byte for null */
        val_size = qry_ptr - val_ptr + 1;

        /* Copy value to the caller's buffer. */
        strlcpy(val, val_ptr, MIN(val_size, buf_len));

        /* If buffer length is smaller than needed, return truncation error */
        if (buf_len < val_size) {
            return ESP_ERR_HTTPD_RESULT_TRUNC;
        }
        return ESP_OK;
    }
    ESP_LOGD(TAG, LOG_FMT("key %s not found"), key);
    return ESP_ERR_NOT_FOUND;
}