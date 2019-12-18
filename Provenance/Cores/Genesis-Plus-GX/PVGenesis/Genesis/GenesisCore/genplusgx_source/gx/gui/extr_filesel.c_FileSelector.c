#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;

/* Type definitions */
struct TYPE_25__ {int selected; int max_buttons; TYPE_4__** arrows; } ;
typedef  TYPE_3__ gui_menu ;
struct TYPE_26__ {int state; int x; int w; int y; int h; } ;
typedef  TYPE_4__ gui_butn ;
struct TYPE_29__ {TYPE_1__* entries; } ;
struct TYPE_24__ {int x; int y; int /*<<< orphan*/  angle; scalar_t__ valid; } ;
struct TYPE_28__ {short keys; TYPE_2__ ir; } ;
struct TYPE_27__ {int width; int height; } ;
struct TYPE_23__ {int filetype; } ;
struct TYPE_22__ {int /*<<< orphan*/  comment; } ;
struct TYPE_21__ {int /*<<< orphan*/  state; TYPE_5__* texture; int /*<<< orphan*/ * data; } ;
struct TYPE_20__ {scalar_t__ bg_overlay; } ;
struct TYPE_19__ {char* filename; scalar_t__ flags; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUTTON_VISIBLE ; 
 char** Cart_dir ; 
 void** Cart_png ; 
 char* DEFAULT_PATH ; 
 int FILETYPE_MAX ; 
 int /*<<< orphan*/  GUI_DeleteMenu (TYPE_3__*) ; 
 int /*<<< orphan*/  GUI_DrawMenu (TYPE_3__*) ; 
 int /*<<< orphan*/  GUI_FadeOut () ; 
 int /*<<< orphan*/  GUI_InitMenu (TYPE_3__*) ; 
 int /*<<< orphan*/  IMAGE_VISIBLE ; 
 int LoadFile (int) ; 
 int MAXPATHLEN ; 
 short PAD_BUTTON_A ; 
 short PAD_BUTTON_B ; 
 short PAD_BUTTON_DOWN ; 
 short PAD_BUTTON_LEFT ; 
 short PAD_BUTTON_RIGHT ; 
 short PAD_BUTTON_UP ; 
 short PAD_TRIGGER_L ; 
 short PAD_TRIGGER_R ; 
 short PAD_TRIGGER_Z ; 
 int ParseDirectory () ; 
 int /*<<< orphan*/  SYS_POWEROFF ; 
 int /*<<< orphan*/  SYS_ResetSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Shutdown ; 
 scalar_t__ UpdateDirectory (int,char*) ; 
 TYPE_15__ action_select ; 
 TYPE_14__* bg_filesel ; 
 TYPE_13__ config ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 TYPE_12__* filelist ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  gxDrawTextureRotate (TYPE_5__*,int,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gxSetScreen () ; 
 int /*<<< orphan*/  gxTextureClose (TYPE_5__**) ; 
 TYPE_5__* gxTextureOpenPNG (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_8__ history ; 
 TYPE_7__ m_input ; 
 int maxfiles ; 
 TYPE_3__ menu_selector ; 
 int offset ; 
 char* prev_folder ; 
 int selection ; 
 int /*<<< orphan*/  shutdown () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ string_offset ; 
 int strlen (char*) ; 
 TYPE_5__* w_pointer ; 

int FileSelector(int type)
{
  short p;
  int i;
  int old = -1;
  char fname[MAXPATHLEN];
  FILE *snap;
  gui_menu *m = &menu_selector;

#ifdef HW_RVL
  int x,y;
  gui_butn *button;
#endif

  /* Background overlay */
  if (config.bg_overlay)
  {
    bg_filesel[1].state |= IMAGE_VISIBLE;
  }
  else
  {
    bg_filesel[1].state &= ~IMAGE_VISIBLE;
  }

  /* Hide all cartridge labels */
  for (i=0; i<FILETYPE_MAX; i++)
  {
    bg_filesel[9+i].state  &= ~IMAGE_VISIBLE;
  }

  /* Cartridge type */
  if (type < 0)
  {
    /* Recent game list -> select all cartridge type */
    for (i=0; i<FILETYPE_MAX; i++)
    {
      bg_filesel[9+i].data = Cart_png[i];
    }
  }
  else
  {
    /* Clear all cartridges type */
    for (i=0; i<FILETYPE_MAX; i++)
    {
      bg_filesel[9+i].data = NULL;
    }

    /* Select cartridge type */
    bg_filesel[9 + type].data = Cart_png[type];
    bg_filesel[9 + type].state |= IMAGE_VISIBLE;
  }

  /* Initialize Menu */
  GUI_InitMenu(m);
  string_offset = 0;

  while (1)
  {
    /* ROM file snapshot/database */
    if (old != selection)
    {
      /* close any existing texture first */
      gxTextureClose(&bg_filesel[8].texture);
      bg_filesel[8].state &= ~IMAGE_VISIBLE;

      old = selection;
      string_offset = 0;

      if (!filelist[selection].flags)
      {
        /* recent game list -> variable game types */
        if (type < 0)
        {
          /* hide all cartridge labels */
          for (i=0; i<FILETYPE_MAX; i++)
          {
            bg_filesel[9+i].state  &= ~IMAGE_VISIBLE;
          }

          /* detect cartridge type */
          type = history.entries[selection].filetype;

          /* show selected cartridge label */
          bg_filesel[9 + type].state |= IMAGE_VISIBLE;

          /*  default screenshot file path */
          sprintf(fname,"%s/snaps/%s/%s", DEFAULT_PATH, Cart_dir[type], filelist[selection].filename);

          /* restore recent type flag */
          type = -1;
        }
        else
        {
          /*  default screenshot file path */
          sprintf(fname,"%s/snaps/%s/%s", DEFAULT_PATH, Cart_dir[type], filelist[selection].filename);
        }

        /* remove original file extension */
        i = strlen(fname) - 1;
        while ((i > 0) && (fname[i] != '.')) i--;
        if (i > 0) fname[i] = 0;

        /* add PNG file extension */
        strcat(fname, ".png");

        /* try to load screenshot file */
        snap = fopen(fname, "rb");
        if (snap)
        {
          bg_filesel[8].texture = gxTextureOpenPNG(0,snap);
          if (bg_filesel[8].texture)
          {
            bg_filesel[8].state |= IMAGE_VISIBLE;
          }
          fclose(snap);
        }
      }
    }

    /* update helper */
    if (m->selected != -1)
    {
      /* out of focus */
      strcpy(action_select.comment,"");
    }
    else if (filelist[selection].flags)
    {
      /* this is a directory */
      strcpy(action_select.comment,"Open Directory");
    }
    else
    {
      /* this is a ROM file */
      strcpy(action_select.comment,"Load File");
    }

    /* Draw menu*/
    GUI_DrawMenu(m);

#ifdef HW_RVL
    if (Shutdown)
    {
      gxTextureClose(&w_pointer);
      GUI_DeleteMenu(m);
      GUI_FadeOut();
      shutdown();
      SYS_ResetSystem(SYS_POWEROFF, 0, 0);
    }
    else if (m_input.ir.valid)
    {
      /* get cursor position */
      x = m_input.ir.x;
      y = m_input.ir.y;

      /* draw wiimote pointer */
      gxDrawTextureRotate(w_pointer, x-w_pointer->width/2, y-w_pointer->height/2, w_pointer->width, w_pointer->height,m_input.ir.angle,255);

      /* ensure we are in the selectable area */
      if ((x < 380) && (y >= 108) && (y <= 368))
      {
        /* find selected item */
        selection = (y - 108) / 26;
        if (selection > 9) selection = 9;
        selection += offset;
        if (selection >= maxfiles) selection = old;

        /* reset selection */
        m->selected = -1;
      }
      else
      {
        /* disable selection */
        m->selected = m->max_buttons + 2;

        /* find selected button */
        for (i=0; i<2; i++)
        {
          button = m->arrows[i];
          if (button)
          {
            if (button->state & BUTTON_VISIBLE)
            {
              if ((x>=button->x)&&(x<=(button->x+button->w))&&(y>=button->y)&&(y<=(button->y+button->h)))
              {
                m->selected = m->max_buttons + i;
                break;
              }
            }
          }
        }
      }
    }
    else
    {
      /* reset selection */
      m->selected = -1;
    }
#endif

    /* copy EFB to XFB */
    gxSetScreen();

    p = m_input.keys;

    /* highlight next item */
    if (p & PAD_BUTTON_DOWN)
    {
      selection++;
      if (selection == maxfiles)
        selection = offset = 0;
      if ((selection - offset) >= 10)
        offset += 10;
    }

    /* highlight previous item */
    else if (p & PAD_BUTTON_UP)
    {
      selection--;
      if (selection < 0)
      {
        selection = maxfiles - 1;
        offset = maxfiles - 10;
      }
      if (selection < offset)
        offset -= 10;
      if (offset < 0)
        offset = 0;
    }

    /* go back one page */
    else if (p & (PAD_TRIGGER_L | PAD_BUTTON_LEFT)) 
    {
      if (maxfiles >= 10)
      {
        selection -= 10;
        if (selection < 0)
        {
          selection = offset = 0;
        }
        else if (selection < offset)
        {
          offset -= 10;
          if (offset < 0) offset = 0;
        }
      }
    }

    /* go forward one page */
    else if (p & (PAD_TRIGGER_R | PAD_BUTTON_RIGHT))
    {
      if (maxfiles >= 10)
      {
        selection += 10;
        if (selection > maxfiles - 1)
        {
          /* last page */
          selection = maxfiles - 1;
          offset = maxfiles - 10;
        }
        else if (selection  >= (offset + 10))
        {
          /* next page */
          offset += 10;
          if (offset > (maxfiles - 10)) offset = maxfiles - 10;
        }
      }
    }

    /* quit */
    else if (p & PAD_TRIGGER_Z)
    {
      GUI_DeleteMenu(m);
      return 0;
    }

    /* previous directory */
    else if (p & PAD_BUTTON_B)
    {
      string_offset = 0;

      /* update browser directory (and get current folder)*/
      if (UpdateDirectory(1, prev_folder))
      {
        /* get directory entries */
        maxfiles = ParseDirectory();

        /* clear selection by default */
        selection = offset = 0;
        old = -1;

        /* select previous directory */
        for (i=0; i<maxfiles; i++)
        {
          if ((filelist[i].flags) && !strcmp(prev_folder,filelist[i].filename))
          {
            selection = i;
            while (i  >= (offset + 10))
            {
              offset += 10;
              if (offset > (maxfiles - 10)) offset = maxfiles - 10;
            }
            break;
          }
        }
      }
      else
      {
        /* exit */
        GUI_DeleteMenu(m);
        return 0;
      }
    }

    /* open selected file or directory */
    else if (p & PAD_BUTTON_A)
    {
      string_offset = 0;

      /* ensure we are in focus area */
      if (m->selected < m->max_buttons)
      {
        if (filelist[selection].flags)
        {
          /* get new directory */
          UpdateDirectory(0, filelist[selection].filename);

          /* get directory entries */
          maxfiles = ParseDirectory();

          /* clear selection by default */
          selection = offset = 0;
          old = -1;
        }
        else
        {  
          /* load ROM file from device */
          int ret = LoadFile(selection);

          /* exit menu */
          GUI_DeleteMenu(m);

          /* return ROM size (or zero if an error occured) */
          return ret;
        }
      }

#ifdef HW_RVL
      /* arrow buttons selected */
      else if (m->selected == m->max_buttons)
      {
        /* up arrow */
        selection--;
        if (selection < 0)
        {
          selection = maxfiles - 1;
          offset = selection - 10 + 1;
        }
        if (selection < offset) offset -= 10;
        if (offset < 0) offset = 0;
      }
      else if (m->selected == (m->max_buttons+1))
      {
        /* down arrow */
        selection++;
        if (selection == maxfiles)
          selection = offset = 0;
        if ((selection - offset) >= 10)
          offset += 10;
      }
#endif
    }
  }
}