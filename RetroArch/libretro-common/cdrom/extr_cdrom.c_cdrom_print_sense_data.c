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

/* Variables and functions */
 unsigned int MIN (size_t,int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void cdrom_print_sense_data(const unsigned char *sense, size_t len)
{
   unsigned i;
   const char *sense_key_text = NULL;
   unsigned char key;
   unsigned char asc;
   unsigned char ascq;

   if (len < 16)
   {
      printf("[CDROM] Sense data buffer length too small.\n");
      fflush(stdout);
      return;
   }

   key = sense[2] & 0xF;
   asc = sense[12];
   ascq = sense[13];

   printf("[CDROM] Sense Data: ");

   for (i = 0; i < MIN(len, 16); i++)
   {
      printf("%02X ", sense[i]);
   }

   printf("\n");

   if (sense[0] == 0x70)
      printf("[CDROM] CURRENT ERROR:\n");
   if (sense[0] == 0x71)
      printf("[CDROM] DEFERRED ERROR:\n");

   switch (key)
   {
      case 0:
         sense_key_text = "NO SENSE";
         break;
      case 1:
         sense_key_text = "RECOVERED ERROR";
         break;
      case 2:
         sense_key_text = "NOT READY";
         break;
      case 3:
         sense_key_text = "MEDIUM ERROR";
         break;
      case 4:
         sense_key_text = "HARDWARE ERROR";
         break;
      case 5:
         sense_key_text = "ILLEGAL REQUEST";
         break;
      case 6:
         sense_key_text = "UNIT ATTENTION";
         break;
      case 7:
         sense_key_text = "DATA PROTECT";
         break;
      case 8:
         sense_key_text = "BLANK CHECK";
         break;
      case 9:
         sense_key_text = "VENDOR SPECIFIC";
         break;
      case 10:
         sense_key_text = "COPY ABORTED";
         break;
      case 11:
         sense_key_text = "ABORTED COMMAND";
         break;
      case 13:
         sense_key_text = "VOLUME OVERFLOW";
         break;
      case 14:
         sense_key_text = "MISCOMPARE";
         break;
   }

   printf("[CDROM] Sense Key: %02X (%s)\n", key, sense_key_text ? sense_key_text : "null");
   printf("[CDROM] ASC: %02X\n", asc);
   printf("[CDROM] ASCQ: %02X\n", ascq);

   switch (key)
   {
      case 2:
      {
         switch (asc)
         {
            case 4:
            {
               switch (ascq)
               {
                  case 1:
                     printf("[CDROM] Description: LOGICAL UNIT IS IN PROCESS OF BECOMING READY\n");
                     break;
                  default:
                     break;
               }

               break;
            }
            case 0x3a:
            {
               switch (ascq)
               {
                  case 0:
                     printf("[CDROM] Description: MEDIUM NOT PRESENT\n");
                     break;
                  case 3:
                     printf("[CDROM] Description: MEDIUM NOT PRESENT - LOADABLE\n");
                     break;
                  case 1:
                     printf("[CDROM] Description: MEDIUM NOT PRESENT - TRAY CLOSED\n");
                     break;
                  case 2:
                     printf("[CDROM] Description: MEDIUM NOT PRESENT - TRAY OPEN\n");
                     break;
                  default:
                     break;
               }

               break;
            }
            default:
               break;
         }
      }
      case 3:
      {
         if (asc == 0x11 && ascq == 0x5)
            printf("[CDROM] Description: L-EC UNCORRECTABLE ERROR\n");
         break;
      }
      case 5:
      {
         if (asc == 0x20 && ascq == 0)
            printf("[CDROM] Description: INVALID COMMAND OPERATION CODE\n");
         else if (asc == 0x24 && ascq == 0)
            printf("[CDROM] Description: INVALID FIELD IN CDB\n");
         else if (asc == 0x26 && ascq == 0)
            printf("[CDROM] Description: INVALID FIELD IN PARAMETER LIST\n");
         break;
      }
      case 6:
      {
         if (asc == 0x28 && ascq == 0)
            printf("[CDROM] Description: NOT READY TO READY CHANGE, MEDIUM MAY HAVE CHANGED\n");
         break;
      }
      default:
         break;
   }

   fflush(stdout);
}