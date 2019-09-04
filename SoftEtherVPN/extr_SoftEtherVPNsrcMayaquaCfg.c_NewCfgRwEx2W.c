#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_4__ {int DontBackup; void* lock; void* Io; void* FileName; void* FileNameW; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CFG_RW ;

/* Variables and functions */
 int /*<<< orphan*/ * CfgReadW (int /*<<< orphan*/ *) ; 
 void* CopyUniStr (int /*<<< orphan*/ *) ; 
 void* CopyUniToStr (int /*<<< orphan*/ *) ; 
 void* FileCreateW (int /*<<< orphan*/ *) ; 
 void* FileOpenW (int /*<<< orphan*/ *,int) ; 
 void* NewLock () ; 
 int UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 TYPE_1__* ZeroMalloc (int) ; 

CFG_RW *NewCfgRwEx2W(FOLDER **root, wchar_t *cfg_name, bool dont_backup, wchar_t *template_name)
{
	CFG_RW *rw;
	FOLDER *f;
	bool loaded_from_template = false;
	// Validate arguments
	if (cfg_name == NULL || root == NULL)
	{
		return NULL;
	}

	f = CfgReadW(cfg_name);
	if (f == NULL)
	{
		// Load from template
		if (UniIsEmptyStr(template_name) == false)
		{
			f = CfgReadW(template_name);
			if (f != NULL)
			{
				loaded_from_template = true;

				goto LABEL_CONTINUE;
			}
		}

		rw = ZeroMalloc(sizeof(CFG_RW));
		rw->lock = NewLock();
		rw->FileNameW = CopyUniStr(cfg_name);
		rw->FileName = CopyUniToStr(cfg_name);
		rw->Io = FileCreateW(cfg_name);
		*root = NULL;
		rw->DontBackup = dont_backup;

		return rw;
	}

LABEL_CONTINUE:
	rw = ZeroMalloc(sizeof(CFG_RW));
	rw->FileNameW = CopyUniStr(cfg_name);
	rw->FileName = CopyUniToStr(cfg_name);
	if (loaded_from_template == false)
	{
		rw->Io = FileOpenW(cfg_name, false);
	}
	else
	{
		rw->Io = FileCreateW(cfg_name);
	}
	rw->lock = NewLock();

	*root = f;

	rw->DontBackup = dont_backup;

	return rw;
}