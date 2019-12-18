#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  graph; int /*<<< orphan*/  output; } ;
typedef  TYPE_1__ hb_filter_private_t ;
struct TYPE_9__ {TYPE_1__* private_data; } ;
typedef  TYPE_2__ hb_filter_object_t ;
struct TYPE_10__ {char* human_readable_desc; int /*<<< orphan*/  output; } ;
typedef  TYPE_3__ hb_filter_info_t ;

/* Variables and functions */
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int global_verbosity_level ; 
 char* hb_avfilter_graph_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 char* malloc (int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static hb_filter_info_t * avfilter_info(hb_filter_object_t * filter)
{
    hb_filter_private_t * pv = filter->private_data;
    hb_filter_info_t    * info;

    if (global_verbosity_level < 2)
    {
        // Only show this for log levels 2 and above
        return NULL;
    }
    if (pv == NULL)
    {
        return NULL;
    }

    info = calloc(1, sizeof(hb_filter_info_t));
    if (info == NULL)
    {
        hb_error("avfilter_info: allocation failure");
        return NULL;
    }
    info->output = pv->output;
    info->human_readable_desc = malloc(1024);
    if (info->human_readable_desc == NULL)
    {
        free(info);
        hb_error("avfilter_info: allocation failure");
        return NULL;
    }
    info->human_readable_desc[0] = 0;

    char       * dst   = info->human_readable_desc;
    const char * start = hb_avfilter_graph_settings(pv->graph);
    while (start != NULL && *start != 0)
    {
        // Find end of a filter
        char * comma = strchr(start, ',');
        char * quote = strchr(start, '\'');
        if (comma != NULL && quote != NULL && quote < comma)
        {
            // Find end of quote
            quote = strchr(quote+1, '\'');
            comma = strchr(start, ',');
        }
        // pretty print line
        int name = 1;
        while (*start != 0 && (comma == NULL || start < comma))
        {
            switch (*start)
            {
                case '=':
                    if (name)
                    {
                        *dst++ = ':';
                        *dst++ = ' ';
                        name = 0;
                    }
                    else
                    {
                        *dst++ = '=';
                    }
                    break;

                case ':':
                    *dst++ = ',';
                    *dst++ = ' ';
                    break;

                case '\'':
                case ' ':
                    break;

                default:
                    *dst++ = *start;

            }
            start++;
        }
        if (*start != 0)
        {
            *dst++ = '\n';
            start++;
        }
    }
    *dst = 0;
    return info;
}