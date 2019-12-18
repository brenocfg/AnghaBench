#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_9__ {char* str; int len; int size; } ;
struct TYPE_8__ {int parent_log_context_offset; int /*<<< orphan*/  (* item_name ) (void*) ;} ;
typedef  TYPE_1__ AVClass ;
typedef  TYPE_2__ AVBPrint ;

/* Variables and functions */
 int AV_BPRINT_SIZE_AUTOMATIC ; 
 int AV_CLASS_CATEGORY_NA ; 
 int AV_LOG_PRINT_LEVEL ; 
 int AV_LOG_QUIET ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  av_vbprintf (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int flags ; 
 int get_category (void*) ; 
 int /*<<< orphan*/  get_level_str (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub2 (void*) ; 

__attribute__((used)) static void format_line(void *avcl, int level, const char *fmt, va_list vl,
                        AVBPrint part[4], int *print_prefix, int type[2])
{
    AVClass* avc = avcl ? *(AVClass **) avcl : NULL;
    av_bprint_init(part+0, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+1, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+2, 0, AV_BPRINT_SIZE_AUTOMATIC);
    av_bprint_init(part+3, 0, 65536);

    if(type) type[0] = type[1] = AV_CLASS_CATEGORY_NA + 16;
    if (*print_prefix && avc) {
        if (avc->parent_log_context_offset) {
            AVClass** parent = *(AVClass ***) (((uint8_t *) avcl) +
                                   avc->parent_log_context_offset);
            if (parent && *parent) {
                av_bprintf(part+0, "[%s @ %p] ",
                         (*parent)->item_name(parent), parent);
                if(type) type[0] = get_category(parent);
            }
        }
        av_bprintf(part+1, "[%s @ %p] ",
                 avc->item_name(avcl), avcl);
        if(type) type[1] = get_category(avcl);
    }

    if (*print_prefix && (level > AV_LOG_QUIET) && (flags & AV_LOG_PRINT_LEVEL))
        av_bprintf(part+2, "[%s] ", get_level_str(level));

    av_vbprintf(part+3, fmt, vl);

    if(*part[0].str || *part[1].str || *part[2].str || *part[3].str) {
        char lastc = part[3].len && part[3].len <= part[3].size ? part[3].str[part[3].len - 1] : 0;
        *print_prefix = lastc == '\n' || lastc == '\r';
    }
}