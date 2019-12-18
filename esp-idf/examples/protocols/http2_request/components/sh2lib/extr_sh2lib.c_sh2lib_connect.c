#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sh2lib_handle {int /*<<< orphan*/  hostname; int /*<<< orphan*/ * http2_tls; } ;
struct http_parser_url {TYPE_1__* field_data; } ;
struct TYPE_5__ {char const** alpn_protos; int non_block; } ;
typedef  TYPE_2__ esp_tls_cfg_t ;
struct TYPE_4__ {size_t off; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  TAG ; 
 size_t UF_HOST ; 
 scalar_t__ do_http2_connect (struct sh2lib_handle*) ; 
 int /*<<< orphan*/ * esp_tls_conn_http_new (char const*,TYPE_2__*) ; 
 int /*<<< orphan*/  http_parser_parse_url (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct http_parser_url*) ; 
 int /*<<< orphan*/  http_parser_url_init (struct http_parser_url*) ; 
 int /*<<< orphan*/  memset (struct sh2lib_handle*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sh2lib_free (struct sh2lib_handle*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strndup (char const*,int /*<<< orphan*/ ) ; 

int sh2lib_connect(struct sh2lib_handle *hd, const char *uri)
{
    memset(hd, 0, sizeof(*hd));
    const char *proto[] = {"h2", NULL};
    esp_tls_cfg_t tls_cfg = {
        .alpn_protos = proto,
        .non_block = true,
    };    
    if ((hd->http2_tls = esp_tls_conn_http_new(uri, &tls_cfg)) == NULL) {
        ESP_LOGE(TAG, "[sh2-connect] esp-tls connection failed");
        goto error;
    }
    struct http_parser_url u;
    http_parser_url_init(&u);
    http_parser_parse_url(uri, strlen(uri), 0, &u);
    hd->hostname = strndup(&uri[u.field_data[UF_HOST].off], u.field_data[UF_HOST].len);

    /* HTTP/2 Connection */
    if (do_http2_connect(hd) != 0) {
        ESP_LOGE(TAG, "[sh2-connect] HTTP2 Connection failed with %s", uri);
        goto error;
    }

    return 0;
error:
    sh2lib_free(hd);
    return -1;
}