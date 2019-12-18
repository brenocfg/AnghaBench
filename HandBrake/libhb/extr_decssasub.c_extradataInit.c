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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;
struct TYPE_5__ {TYPE_1__* subtitle; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_4__ {int extradata_size; int /*<<< orphan*/ * extradata; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int hb_getline (char**,size_t*,int /*<<< orphan*/ ) ; 
 char* hb_strdup_printf (char*,char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int) ; 

__attribute__((used)) static int extradataInit( hb_work_private_t * pv )
{
    int    events = 0;
    char * events_tag = "[Events]";
    char * format_tag = "Format:";
    int    events_len = strlen(events_tag);;
    int    format_len = strlen(format_tag);;
    char * header = NULL;

    while (1)
    {
        char    * line = NULL;
        ssize_t   len;
        size_t    size = 0;

        len = hb_getline(&line, &size, pv->file);
        if (len < 0)
        {
            // Incomplete SSA header
            free(header);
            return 1;
        }
        if (len > 0 && line != NULL)
        {
            if (header != NULL)
            {
                char * tmp = header;
                header = hb_strdup_printf("%s%s", header, line);
                free(tmp);
            }
            else
            {
                header = strdup(line);
            }
            if (!events)
            {
                if (len >= events_len &&
                    !strncasecmp(line, events_tag, events_len))
                {
                    events = 1;
                }
            }
            else
            {
                if (len >= format_len &&
                    !strncasecmp(line, format_tag, format_len))
                {
                    free(line);
                    break;
                }
                // Improperly formatted SSA header
                free(header);
                return 1;
            }
        }
        free(line);
    }
    pv->subtitle->extradata = (uint8_t*)header;
    pv->subtitle->extradata_size = strlen(header) + 1;

    return 0;
}