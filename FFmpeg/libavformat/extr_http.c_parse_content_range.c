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
struct TYPE_4__ {scalar_t__ is_streamed; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int filesize; int seekable; int /*<<< orphan*/  is_akamai; void* off; } ;
typedef  TYPE_2__ HTTPContext ;

/* Variables and functions */
 char* strchr (char const*,char) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 void* strtoull (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void parse_content_range(URLContext *h, const char *p)
{
    HTTPContext *s = h->priv_data;
    const char *slash;

    if (!strncmp(p, "bytes ", 6)) {
        p     += 6;
        s->off = strtoull(p, NULL, 10);
        if ((slash = strchr(p, '/')) && strlen(slash) > 0)
            s->filesize = strtoull(slash + 1, NULL, 10);
    }
    if (s->seekable == -1 && (!s->is_akamai || s->filesize != 2147483647))
        h->is_streamed = 0; /* we _can_ in fact seek */
}