#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct http_parser_url {int field_set; TYPE_1__* field_data; } ;
struct httpd_req_aux {struct http_parser_url url_parse_res; } ;
struct TYPE_6__ {struct httpd_req_aux* aux; } ;
typedef  TYPE_2__ httpd_req_t ;
struct TYPE_5__ {size_t len; } ;

/* Variables and functions */
 int UF_QUERY ; 
 int /*<<< orphan*/  httpd_valid_req (TYPE_2__*) ; 

size_t httpd_req_get_url_query_len(httpd_req_t *r)
{
    if (r == NULL) {
        return 0;
    }

    if (!httpd_valid_req(r)) {
        return 0;
    }

    struct httpd_req_aux   *ra  = r->aux;
    struct http_parser_url *res = &ra->url_parse_res;

    /* Check if query field is present in the URL */
    if (res->field_set & (1 << UF_QUERY)) {
        return res->field_data[UF_QUERY].len;
    }
    return 0;
}