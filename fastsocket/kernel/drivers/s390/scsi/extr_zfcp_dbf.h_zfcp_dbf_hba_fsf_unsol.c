#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zfcp_dbf {TYPE_1__* hba; } ;
struct fsf_status_read_buffer {int dummy; } ;
struct TYPE_2__ {int level; } ;

/* Variables and functions */
 int /*<<< orphan*/  _zfcp_dbf_hba_fsf_unsol (char const*,int,struct zfcp_dbf*,struct fsf_status_read_buffer*) ; 

__attribute__((used)) static inline
void zfcp_dbf_hba_fsf_unsol(const char *tag, struct zfcp_dbf *dbf,
			    struct fsf_status_read_buffer *buf)
{
	int level = 2;

	if (level <= dbf->hba->level)
		_zfcp_dbf_hba_fsf_unsol(tag, level, dbf, buf);
}