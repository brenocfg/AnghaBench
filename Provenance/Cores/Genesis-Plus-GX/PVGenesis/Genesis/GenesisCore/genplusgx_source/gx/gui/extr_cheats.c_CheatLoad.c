#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int enable; scalar_t__* text; scalar_t__* code; } ;
struct TYPE_7__ {scalar_t__ autocheat; } ;
struct TYPE_6__ {TYPE_1__* buttons; } ;
struct TYPE_5__ {int* shift; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTON_ACTIVE ; 
 char* DEFAULT_PATH ; 
 int MAX_CHEATS ; 
 int MAX_DESC_LENGTH ; 
 int /*<<< orphan*/  apply_cheats () ; 
 TYPE_4__* cheatlist ; 
 TYPE_3__ config ; 
 int decode_cheat (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int maxcheats ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ menu_cheats ; 
 scalar_t__ offset ; 
 char* rom_filename ; 
 scalar_t__ selection ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char*,int) ; 

void CheatLoad(void)
{
  int len;
  int cnt = 0;
  char temp[256];

  /* reset cheat count */
  maxcheats = 0;
  
  /* make cheat filename */
  sprintf(temp, "%s/cheats/%s.pat", DEFAULT_PATH, rom_filename);

  /* open file */
  FILE *f = fopen(temp, "r");
  if (f)
  {
    /* clear string */
    memset(temp, 0, 256);

    /* read cheats from file (one line per cheat) */
    while (fgets(temp, 256, f) && (maxcheats < MAX_CHEATS) && (cnt < MAX_CHEATS))
    {
      /* remove CR & EOL chars */
      if ((temp[strlen(temp) - 2] == 0x0d) || (temp[strlen(temp) - 2] == 0x0a)) temp[strlen(temp) - 2] = 0;
      else temp[strlen(temp) - 1] = 0;

      /* check cheat validty */
      len = decode_cheat(temp, maxcheats);

      if (len)
      {
        /* copy cheat code */
        strncpy(cheatlist[maxcheats].code, temp, len);
        cheatlist[maxcheats].code[len] = 0;
        len++;

        /* jump TAB and SPACE characters */
        while ((temp[len] == 0x20) || (temp[len] == 0x09)) len++;

        /* copy cheat description */
        strncpy(cheatlist[maxcheats].text, &temp[len], MAX_DESC_LENGTH - 1);
        cheatlist[maxcheats].text[MAX_DESC_LENGTH - 1] = 0;

        /* increment cheat count */
        maxcheats++;
      }
      else if (!strcmp(temp,"ON") && config.autocheat)
      {
        /* enable flag */
        cheatlist[cnt++].enable = 1;
      }
      else if (!strcmp(temp,"OFF") && config.autocheat)
      {
        /* disable flag */
        cheatlist[cnt++].enable = 0;
      }
    }

    /* by default, disable cheats that were not flagged */
    while (cnt < maxcheats) cheatlist[cnt++].enable = 0;

    /* close file */
    fclose(f);
  }

  /* apply ROM patches */
  apply_cheats();

  /* adjust menu buttons */
  for (cnt=0; cnt<10; cnt++)
  {
    if (cnt < maxcheats)
    {
      menu_cheats.buttons[cnt].state |= BUTTON_ACTIVE;
      menu_cheats.buttons[cnt].shift[1] = 1;
    }
    else if (cnt == maxcheats)
    {
      menu_cheats.buttons[cnt].state |= BUTTON_ACTIVE;
      menu_cheats.buttons[cnt].shift[1] = 0;
    }
    else
    {
      menu_cheats.buttons[cnt].shift[1] = 0;
      menu_cheats.buttons[cnt].state &= ~BUTTON_ACTIVE;
    }
  }

  /* reset menu */
  selection = offset = 0;
}