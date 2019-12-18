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
typedef  int /*<<< orphan*/  XML_Parser ;
typedef  int /*<<< orphan*/  XML_Char ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  READ_SIZE ; 
 int /*<<< orphan*/  const* T (char*) ; 
 scalar_t__ XML_GetBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XML_ParseBuffer (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ XML_STATUS_ERROR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  ftprintf (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int read (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reportError (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stderr ; 
 int topen (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  tperror (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
processStream(const XML_Char *filename, XML_Parser parser)
{
  /* passing NULL for filename means read intput from stdin */
  int fd = 0;   /* 0 is the fileno for stdin */

  if (filename != NULL) {
    fd = topen(filename, O_BINARY|O_RDONLY);
    if (fd < 0) {
      tperror(filename);
      return 0;
    }
  }
  for (;;) {
    int nread;
    char *buf = (char *)XML_GetBuffer(parser, READ_SIZE);
    if (!buf) {
      if (filename != NULL)
        close(fd);
      ftprintf(stderr, T("%s: out of memory\n"),
               filename != NULL ? filename : T("xmlwf"));
      return 0;
    }
    nread = read(fd, buf, READ_SIZE);
    if (nread < 0) {
      tperror(filename != NULL ? filename : T("STDIN"));
      if (filename != NULL)
        close(fd);
      return 0;
    }
    if (XML_ParseBuffer(parser, nread, nread == 0) == XML_STATUS_ERROR) {
        reportError(parser, filename != NULL ? filename : T("STDIN"));
      if (filename != NULL)
        close(fd);
      return 0;
    }
    if (nread == 0) {
      if (filename != NULL)
        close(fd);
      break;;
    }
  }
  return 1;
}