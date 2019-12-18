#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {char* filepath; char* filename; int /*<<< orphan*/  filetype; } ;
typedef  TYPE_1__ t_history_entry ;
struct TYPE_6__ {TYPE_1__* entries; } ;

/* Variables and functions */
 int MAXJOLIET ; 
 int NUM_HISTORY_ENTRIES ; 
 TYPE_4__ history ; 
 int /*<<< orphan*/  history_save () ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

void history_add_file(char *filepath, char *filename, u8 filetype)
{
  /* Create the new entry for this path. */
  t_history_entry newentry;
  strncpy(newentry.filepath, filepath, MAXJOLIET - 1);
  strncpy(newentry.filename, filename, MAXJOLIET - 1);
  newentry.filepath[MAXJOLIET - 1] = '\0';
  newentry.filename[MAXJOLIET - 1] = '\0';
  newentry.filetype = filetype;
  
  t_history_entry oldentry;  /* Old entry is the one being shuffled down a spot. */  
  t_history_entry currentry;  /* Curr entry is the one that just replaced old path. */
  
  /* Initially set curr entry to the new value. */
  memcpy(&currentry, &newentry, sizeof(t_history_entry));

  int i;
  for(i=0; i < NUM_HISTORY_ENTRIES; i++)
  {
    /* Save off the next entry. */
    memcpy(&oldentry, &history.entries[i], sizeof(t_history_entry));

    /* Overwrite with the previous entry. */
    memcpy(&history.entries[i], &currentry, sizeof(t_history_entry));

    /* Switch the old entry to the curr entry now. */
    memcpy(&currentry, &oldentry, sizeof(t_history_entry));

    /* If the entry in the list at this spot matches
       the new entry then do nothing and let this
       entry get deleted. */
    if(strcmp(newentry.filepath, currentry.filepath) == 0 && strcmp(newentry.filename, currentry.filename) == 0)
      break;
  }

  /* now save to disk */
  history_save();
}