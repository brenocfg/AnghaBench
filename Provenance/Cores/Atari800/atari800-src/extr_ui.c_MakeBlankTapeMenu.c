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
typedef  int /*<<< orphan*/  description ;
struct TYPE_2__ {int /*<<< orphan*/  (* fEditString ) (char*,char*,int) ;int /*<<< orphan*/  (* fGetSaveFilename ) (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CASSETTE_CreateCAS (char*,char*) ; 
 int CASSETTE_DESCRIPTION_MAX ; 
 int /*<<< orphan*/  CASSETTE_filename ; 
 int /*<<< orphan*/  CantSave (char*) ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  UI_atari_files_dir ; 
 TYPE_1__* UI_driver ; 
 int /*<<< orphan*/  UI_n_atari_files_dir ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (char*,char*,int) ; 

__attribute__((used)) static void MakeBlankTapeMenu(void)
{
	char filenm[FILENAME_MAX];
	char description[CASSETTE_DESCRIPTION_MAX];
	description[0] = '\0';
	strncpy(filenm, CASSETTE_filename, FILENAME_MAX);
	if (!UI_driver->fGetSaveFilename(filenm, UI_atari_files_dir, UI_n_atari_files_dir))
		return;
	if (!UI_driver->fEditString("Enter tape's description", description, sizeof(description)))
		return;
	if (!CASSETTE_CreateCAS(filenm, description))
		CantSave(filenm);
}