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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int sscanf (char const*,char*,float*,char*,int*) ; 

__attribute__((used)) static uint32_t get_duration_insec(AVFormatContext *s, const char *duration)
{
    /* ISO-8601 duration parser */
    uint32_t days = 0;
    uint32_t hours = 0;
    uint32_t mins = 0;
    uint32_t secs = 0;
    int size = 0;
    float value = 0;
    char type = '\0';
    const char *ptr = duration;

    while (*ptr) {
        if (*ptr == 'P' || *ptr == 'T') {
            ptr++;
            continue;
        }

        if (sscanf(ptr, "%f%c%n", &value, &type, &size) != 2) {
            av_log(s, AV_LOG_WARNING, "get_duration_insec get a wrong time format\n");
            return 0; /* parser error */
        }
        switch (type) {
            case 'D':
                days = (uint32_t)value;
                break;
            case 'H':
                hours = (uint32_t)value;
                break;
            case 'M':
                mins = (uint32_t)value;
                break;
            case 'S':
                secs = (uint32_t)value;
                break;
            default:
                // handle invalid type
                break;
        }
        ptr += size;
    }
    return  ((days * 24 + hours) * 60 + mins) * 60 + secs;
}