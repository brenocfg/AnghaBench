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

/* Variables and functions */
 int /*<<< orphan*/  av_strcasecmp (char const*,char*) ; 
 char* avio_find_protocol_name (char*) ; 

int ff_is_http_proto(char *filename) {
    const char *proto = avio_find_protocol_name(filename);
    return proto ? (!av_strcasecmp(proto, "http") || !av_strcasecmp(proto, "https")) : 0;
}