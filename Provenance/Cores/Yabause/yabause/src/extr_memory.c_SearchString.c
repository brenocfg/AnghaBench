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
typedef  char u8 ;
typedef  int u32 ;
typedef  char u16 ;
typedef  int /*<<< orphan*/  result_struct ;

/* Variables and functions */
 int /*<<< orphan*/  MappedMemoryAddMatch (int,char,int,int /*<<< orphan*/ *,int*) ; 
 char MappedMemoryReadByte (int) ; 
 char MappedMemoryReadWord (int) ; 
#define  SEARCHREL16BIT 130 
#define  SEARCHREL8BIT 129 
#define  SEARCHSTRING 128 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* strtok (char*,char*) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SearchString(u32 startaddr, u32 endaddr, int searchtype,
                        const char *searchstr, result_struct *results,
                        u32 *maxresults)
{
   u8 *buf=NULL;
   u32 *buf32=NULL;
   u32 buflen=0;
   u32 counter;
   u32 addr;
   u32 numresults=0;

   buflen=(u32)strlen(searchstr);

   if ((buf32=(u32 *)malloc(buflen*sizeof(u32))) == NULL)
      return 0;

   buf = (u8 *)buf32;

   // Copy string to buffer
   switch (searchtype & 0x70)
   {
      case SEARCHSTRING:
         strcpy((char *)buf, searchstr);
         break;
      case SEARCHREL8BIT:
      case SEARCHREL16BIT:
      {
         char *text;
         char *searchtext=strdup(searchstr);

         // Calculate buffer length and read values into table
         buflen = 0;
         for (text=strtok((char *)searchtext, " ,"); text != NULL; text=strtok(NULL, " ,"))
         {
            buf32[buflen] = strtoul(text, NULL, 0);
            buflen++;
         }
         free(searchtext);

         break;
      }
   }

   addr = startaddr;
   counter = 0;

   for (;;)
   {
      // Fetch byte/word/etc.
      switch (searchtype & 0x70)
      {
         case SEARCHSTRING:
         {
            u8 val = MappedMemoryReadByte(addr);
            addr++;

            if (val == buf[counter])
            {
               counter++;
               if (counter == buflen)
                  MappedMemoryAddMatch(addr-buflen, val, searchtype, results, &numresults);
            }
            else
               counter = 0;
            break;
         }
         case SEARCHREL8BIT:
         {
            int diff;
            u32 j;
            u8 val2;
            u8 val = MappedMemoryReadByte(addr);

            for (j = 1; j < buflen; j++)
            {
               // grab the next value
               val2 = MappedMemoryReadByte(addr+j);

               // figure out the diff
               diff = (int)val2 - (int)val;

               // see if there's a match
               if (((int)buf32[j] - (int)buf32[j-1]) != diff)
                  break;

               if (j == (buflen - 1))
                  MappedMemoryAddMatch(addr, val, searchtype, results, &numresults);

               val = val2;
            }

            addr++;

            break;
         }
         case SEARCHREL16BIT:
         {
            int diff;
            u32 j;
            u16 val2;
            u16 val = MappedMemoryReadWord(addr);

            for (j = 1; j < buflen; j++)
            {
               // grab the next value
               val2 = MappedMemoryReadWord(addr+(j*2));

               // figure out the diff
               diff = (int)val2 - (int)val;

               // see if there's a match
               if (((int)buf32[j] - (int)buf32[j-1]) != diff)
                  break;

               if (j == (buflen - 1))
                  MappedMemoryAddMatch(addr, val, searchtype, results, &numresults);

               val = val2;
            }

            addr+=2;
            break;
         }
      }

      if (addr > endaddr || numresults >= maxresults[0])
         break;
   }

   free(buf);
   maxresults[0] = numresults;
   return 1;
}