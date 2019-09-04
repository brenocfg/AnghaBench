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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static char *local_getline(char *zPrompt, FILE *in, int csvFlag){
  char *zLine;
  int nLine;
  int n;
  int inQuote = 0;

  if( zPrompt && *zPrompt ){
    printf("%s",zPrompt);
    fflush(stdout);
  }
  nLine = 100;
  zLine = malloc( nLine );
  if( zLine==0 ) return 0;
  n = 0;
  while( 1 ){
    if( n+100>nLine ){
      nLine = nLine*2 + 100;
      zLine = realloc(zLine, nLine);
      if( zLine==0 ) return 0;
    }
    if( fgets(&zLine[n], nLine - n, in)==0 ){
      if( n==0 ){
        free(zLine);
        return 0;
      }
      zLine[n] = 0;
      break;
    }
    while( zLine[n] ){
      if( zLine[n]=='"' ) inQuote = !inQuote;
      n++;
    }
    if( n>0 && zLine[n-1]=='\n' && (!inQuote || !csvFlag) ){
      n--;
      if( n>0 && zLine[n-1]=='\r' ) n--;
      zLine[n] = 0;
      break;
    }
  }
  zLine = realloc( zLine, n+1 );
  return zLine;
}