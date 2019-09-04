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
struct callback_data {char const* nullvalue; char const* separator; int /*<<< orphan*/ * out; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 scalar_t__* needCsvQuote ; 
 int /*<<< orphan*/  putc (char const,int /*<<< orphan*/ *) ; 
 int strlen30 (char const*) ; 

__attribute__((used)) static void output_csv(struct callback_data *p, const char *z, int bSep){
  FILE *out = p->out;
  if( z==0 ){
    fprintf(out,"%s",p->nullvalue);
  }else{
    int i;
    int nSep = strlen30(p->separator);
    for(i=0; z[i]; i++){
      if( needCsvQuote[((unsigned char*)z)[i]] 
         || (z[i]==p->separator[0] && 
             (nSep==1 || memcmp(z, p->separator, nSep)==0)) ){
        i = 0;
        break;
      }
    }
    if( i==0 ){
      putc('"', out);
      for(i=0; z[i]; i++){
        if( z[i]=='"' ) putc('"', out);
        putc(z[i], out);
      }
      putc('"', out);
    }else{
      fprintf(out, "%s", z);
    }
  }
  if( bSep ){
    fprintf(p->out, "%s", p->separator);
  }
}