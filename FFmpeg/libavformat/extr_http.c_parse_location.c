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
typedef  int /*<<< orphan*/  redirected_location ;
struct TYPE_3__ {char* location; } ;
typedef  TYPE_1__ HTTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int MAX_URL_SIZE ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_strdup (char*) ; 
 int /*<<< orphan*/  ff_make_absolute_url (char*,int,char*,char const*) ; 

__attribute__((used)) static int parse_location(HTTPContext *s, const char *p)
{
    char redirected_location[MAX_URL_SIZE], *new_loc;
    ff_make_absolute_url(redirected_location, sizeof(redirected_location),
                         s->location, p);
    new_loc = av_strdup(redirected_location);
    if (!new_loc)
        return AVERROR(ENOMEM);
    av_free(s->location);
    s->location = new_loc;
    return 0;
}