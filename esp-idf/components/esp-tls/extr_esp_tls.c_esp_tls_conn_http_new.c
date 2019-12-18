#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct http_parser_url {TYPE_1__* field_data; } ;
typedef  int /*<<< orphan*/  esp_tls_t ;
typedef  int /*<<< orphan*/  esp_tls_cfg_t ;
struct TYPE_2__ {size_t off; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 size_t UF_HOST ; 
 int esp_tls_conn_new_sync (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * esp_tls_init () ; 
 int /*<<< orphan*/  get_port (char const*,struct http_parser_url*) ; 
 int /*<<< orphan*/  http_parser_parse_url (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct http_parser_url*) ; 
 int /*<<< orphan*/  http_parser_url_init (struct http_parser_url*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

esp_tls_t *esp_tls_conn_http_new(const char *url, const esp_tls_cfg_t *cfg)
{
    /* Parse URI */
    struct http_parser_url u;
    http_parser_url_init(&u);
    http_parser_parse_url(url, strlen(url), 0, &u);
    esp_tls_t *tls = esp_tls_init();
    if (!tls) {
        return NULL;
    }
    /* Connect to host */
    if (esp_tls_conn_new_sync(&url[u.field_data[UF_HOST].off], u.field_data[UF_HOST].len,
                              get_port(url, &u), cfg, tls) == 1) {
        return tls;
    }
    return NULL;
}