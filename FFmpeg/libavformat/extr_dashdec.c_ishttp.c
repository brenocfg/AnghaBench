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
 int av_strstart (char const*,char*,int /*<<< orphan*/ *) ; 
 char* avio_find_protocol_name (char*) ; 

__attribute__((used)) static int ishttp(char *url)
{
    const char *proto_name = avio_find_protocol_name(url);
    return av_strstart(proto_name, "http", NULL);
}