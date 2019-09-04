#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int verify; void* key_file; void* cert_file; void* ca_file; } ;
typedef  TYPE_1__ TLSShared ;

/* Variables and functions */
 scalar_t__ av_find_info_tag (char*,int,char*,char const*) ; 
 void* av_strdup (char*) ; 
 char* strchr (char const*,char) ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static void set_options(TLSShared *c, const char *uri)
{
    char buf[1024];
    const char *p = strchr(uri, '?');
    if (!p)
        return;

    if (!c->ca_file && av_find_info_tag(buf, sizeof(buf), "cafile", p))
        c->ca_file = av_strdup(buf);

    if (!c->verify && av_find_info_tag(buf, sizeof(buf), "verify", p)) {
        char *endptr = NULL;
        c->verify = strtol(buf, &endptr, 10);
        if (buf == endptr)
            c->verify = 1;
    }

    if (!c->cert_file && av_find_info_tag(buf, sizeof(buf), "cert", p))
        c->cert_file = av_strdup(buf);

    if (!c->key_file && av_find_info_tag(buf, sizeof(buf), "key", p))
        c->key_file = av_strdup(buf);
}