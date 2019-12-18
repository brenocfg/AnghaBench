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
struct winsize {int ws_ypixel; int ws_row; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct termios {int c_lflag; int* c_cc; } ;
typedef  int /*<<< orphan*/  old_termios ;

/* Variables and functions */
 int ECHO ; 
 int ICANON ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TIOCGWINSZ ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct winsize*) ; 
 int /*<<< orphan*/  memcpy (struct termios*,struct termios*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int scanf (char*,int*,int*) ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 
 int wait_stdin (int) ; 

__attribute__((used)) static void scroll_on_demand(int pixelheight)
{
#ifdef HAVE_SYS_IOCTL_H
   struct winsize size = {0, 0, 0, 0};
#endif
#ifdef HAVE_TERMIOS_H
   struct termios old_termios;
   struct termios new_termios;
#endif
   int row = 0;
   int col = 0;
   int cellheight;
   int scroll;

#ifdef HAVE_SYS_IOCTL_H
   ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
   if (size.ws_ypixel <= 0)
   {
      printf("\033[H\0337");
      return;
   }
# ifdef HAVE_TERMIOS_H
   /* set the terminal to cbreak mode */
   tcgetattr(STDIN_FILENO, &old_termios);
   memcpy(&new_termios, &old_termios, sizeof(old_termios));
   new_termios.c_lflag &= ~(ECHO | ICANON);
   new_termios.c_cc[VMIN] = 1;
   new_termios.c_cc[VTIME] = 0;
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);

   /* request cursor position report */
   printf("\033[6n");

   if (wait_stdin(1000 * 1000) != (-1))
   {
      /* wait 1 sec */
      if (scanf("\033[%d;%dR", &row, &col) == 2)
      {
         cellheight = pixelheight * size.ws_row / size.ws_ypixel + 1;
         scroll = cellheight + row - size.ws_row + 1;
         printf("\033[%dS\033[%dA", scroll, scroll);
         printf("\0337");
      }
      else
      {
         printf("\033[H\0337");
      }
   }

   tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios);
# else
   printf("\033[H\0337");
# endif  /* HAVE_TERMIOS_H */
#else
   printf("\033[H\0337");
#endif  /* HAVE_SYS_IOCTL_H */
}