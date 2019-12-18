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
struct TYPE_3__ {int /*<<< orphan*/  features; } ;
typedef  TYPE_1__ FTPContext ;

/* Variables and functions */
 int /*<<< orphan*/ * av_stristr (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int ftp_has_feature(FTPContext *s, const char *feature_name)
{
    if (!s->features)
        return 0;

    return av_stristr(s->features, feature_name) != NULL;
}