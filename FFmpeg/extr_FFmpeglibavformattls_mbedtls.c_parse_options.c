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
struct TYPE_3__ {int /*<<< orphan*/  priv_key_pw; } ;
typedef  TYPE_1__ TLSContext ;

/* Variables and functions */
 scalar_t__ av_find_info_tag (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  av_strdup (char*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void parse_options(TLSContext *tls_ctxc, const char *uri)
{
    char buf[1024];
    const char *p = strchr(uri, '?');
    if (!p)
        return;

    if (!tls_ctxc->priv_key_pw && av_find_info_tag(buf, sizeof(buf), "key_password", p))
        tls_ctxc->priv_key_pw = av_strdup(buf);
}