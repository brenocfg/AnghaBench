#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  file_name ;
typedef  int /*<<< orphan*/  current_file_name ;
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
struct TYPE_20__ {int num_item; } ;
struct TYPE_19__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_18__ {scalar_t__ CurrentFilePointer; int log_number_incremented; int CurrentLogNumber; int /*<<< orphan*/  DirName; int /*<<< orphan*/  SwitchType; int /*<<< orphan*/  Prefix; int /*<<< orphan*/  FlushEvent; TYPE_6__* RecordQueue; } ;
struct TYPE_17__ {int /*<<< orphan*/  Tick; } ;
typedef  TYPE_1__ RECORD ;
typedef  TYPE_2__ LOG ;
typedef  int /*<<< orphan*/  IO ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ClearBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  FileCloseEx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * FileCreate (char*) ; 
 int /*<<< orphan*/ * FileOpen (char*,int) ; 
 int /*<<< orphan*/  FileSeek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* FileSize64 (int /*<<< orphan*/ *) ; 
 int FileWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 scalar_t__ GetMaxLogSize () ; 
 TYPE_1__* GetNext (TYPE_6__*) ; 
 int IsFileExists (char*) ; 
 scalar_t__ LOG_ENGINE_BUFFER_CACHE_SIZE_MAX ; 
 int LOG_ENGINE_SAVE_START_CACHE_COUNT ; 
 int /*<<< orphan*/  LockLog (TYPE_2__*) ; 
 int /*<<< orphan*/  LockQueue (TYPE_6__*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MakeDir (int /*<<< orphan*/ ) ; 
 int MakeLogFileName (TYPE_2__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  MsSetThreadPriorityIdle () ; 
 int /*<<< orphan*/  MsSetThreadPriorityRealtime () ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 scalar_t__ StrCmp (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UnlockLog (TYPE_2__*) ; 
 int /*<<< orphan*/  UnlockQueue (TYPE_6__*) ; 
 int /*<<< orphan*/  Win32SetFolderCompress (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteRecordToBuffer (TYPE_3__*,TYPE_1__*) ; 

__attribute__((used)) static bool LogThreadWriteGeneral(LOG *log_object, BUF *buffer, IO **io, bool *log_date_changed, char *current_logfile_datename, char *current_file_name)
{
	RECORD *rec;
	char file_name[MAX_SIZE];
	UINT num;

	// Retrieve a record from the head of the queue
	LockQueue(log_object->RecordQueue);
	{
		rec = GetNext(log_object->RecordQueue);
		num = log_object->RecordQueue->num_item;
	}
	UnlockQueue(log_object->RecordQueue);

#ifdef	OS_WIN32
	if (num >= LOG_ENGINE_SAVE_START_CACHE_COUNT)
	{
		// Raise the priority
		Debug("LOG_THREAD: MsSetThreadPriorityRealtime\n");
		MsSetThreadPriorityRealtime();
	}

	if (num < (LOG_ENGINE_SAVE_START_CACHE_COUNT / 2))
	{
		// Restore the priority
		Debug("LOG_THREAD: MsSetThreadPriorityIdle\n");
		MsSetThreadPriorityIdle();
	}
#endif	// OS_WIN32

	if (buffer->Size > GetMaxLogSize())
	{
		// Erase if the size of the buffer is larger than the maximum log file size
		ClearBuf(buffer);
	}

	if (buffer->Size >= LOG_ENGINE_BUFFER_CACHE_SIZE_MAX)
	{
		// Write the contents of the buffer to the file
		if (*io != NULL)
		{
			if ((log_object->CurrentFilePointer + (UINT64)buffer->Size) > GetMaxLogSize())
			{
				if (log_object->log_number_incremented == false)
				{
					log_object->CurrentLogNumber++;
					log_object->log_number_incremented = true;
				}
			}
			else
			{
				if (FileWrite(*io, buffer->Buf, buffer->Size) == false)
				{
					FileCloseEx(*io, true);
					// If it fails to write to the file,
					// erase the buffer and give up
					ClearBuf(buffer);
					*io = NULL;
				}
				else
				{
					log_object->CurrentFilePointer += (UINT64)buffer->Size;
					ClearBuf(buffer);
				}
			}
		}
	}

	if (rec == NULL)
	{
		if (buffer->Size != 0)
		{
			// Write the contents of the buffer to the file
			if (*io != NULL)
			{
				if ((log_object->CurrentFilePointer + (UINT64)buffer->Size) > GetMaxLogSize())
				{
					if (log_object->log_number_incremented == false)
					{
						log_object->CurrentLogNumber++;
						log_object->log_number_incremented = true;
					}
				}
				else
				{
					if (FileWrite(*io, buffer->Buf, buffer->Size) == false)
					{
						FileCloseEx(*io, true);
						// If it fails to write to the file,
						// erase the buffer and give up
						ClearBuf(buffer);
						*io = NULL;
					}
					else
					{
						log_object->CurrentFilePointer += (UINT64)buffer->Size;
						ClearBuf(buffer);
					}
				}
			}
		}

		Set(log_object->FlushEvent);
		return false;
	}

	// Generate a log file name
	LockLog(log_object);
	{
		*log_date_changed = MakeLogFileName(log_object, file_name, sizeof(file_name),
			log_object->DirName, log_object->Prefix, rec->Tick, log_object->SwitchType, log_object->CurrentLogNumber, current_logfile_datename);

		if (*log_date_changed)
		{
			UINT i;

			log_object->CurrentLogNumber = 0;
			MakeLogFileName(log_object, file_name, sizeof(file_name),
				log_object->DirName, log_object->Prefix, rec->Tick, log_object->SwitchType, 0, current_logfile_datename);
			for (i = 0;;i++)
			{
				char tmp[MAX_SIZE];
				MakeLogFileName(log_object, tmp, sizeof(tmp),
					log_object->DirName, log_object->Prefix, rec->Tick, log_object->SwitchType, i, current_logfile_datename);

				if (IsFileExists(tmp) == false)
				{
					break;
				}
				StrCpy(file_name, sizeof(file_name), tmp);
				log_object->CurrentLogNumber = i;
			}
		}
	}
	UnlockLog(log_object);

	if (*io != NULL)
	{
		if (StrCmp(current_file_name, file_name) != 0)
		{
			// If a log file is currently opened and writing to another log
			// file is needed for this time, write the contents of the 
			//buffer and close the log file. Write the contents of the buffer
			if (*io != NULL)
			{
				if (*log_date_changed)
				{
					if ((log_object->CurrentFilePointer + (UINT64)buffer->Size) <= GetMaxLogSize())
					{
						if (FileWrite(*io, buffer->Buf, buffer->Size) == false)
						{
							FileCloseEx(*io, true);
							ClearBuf(buffer);
							*io = NULL;
						}
						else
						{
							log_object->CurrentFilePointer += (UINT64)buffer->Size;
							ClearBuf(buffer);
						}
					}
				}
				// Close the file
				FileCloseEx(*io, true);
			}

			log_object->log_number_incremented = false;

			// Open or create a new log file
			StrCpy(current_file_name, sizeof(current_file_name), file_name);
			*io = FileOpen(file_name, true);
			if (*io == NULL)
			{
				// Create a log file
				LockLog(log_object);
				{
					MakeDir(log_object->DirName);

#ifdef	OS_WIN32
					Win32SetFolderCompress(log_object->DirName, true);
#endif	// OS_WIN32
				}
				UnlockLog(log_object);
				*io = FileCreate(file_name);
				log_object->CurrentFilePointer = 0;
			}
			else
			{
				// Seek to the end of the log file
				log_object->CurrentFilePointer = FileSize64(*io);
				FileSeek(*io, SEEK_END, 0);
			}
		}
	}
	else
	{
		// Open or create a new log file
		StrCpy(current_file_name, sizeof(current_file_name), file_name);
		*io = FileOpen(file_name, true);
		if (*io == NULL)
		{
			// Create a log file
			LockLog(log_object);
			{
				MakeDir(log_object->DirName);
#ifdef	OS_WIN32
				Win32SetFolderCompress(log_object->DirName, true);
#endif	// OS_WIN32
			}
			UnlockLog(log_object);
			*io = FileCreate(file_name);
			log_object->CurrentFilePointer = 0;
			if (*io == NULL)
			{
				//Debug("Logging.c: SleepThread(30);\n");
				SleepThread(30);
			}
		}
		else
		{
			// Seek to the end of the log file
			log_object->CurrentFilePointer = FileSize64(*io);
			FileSeek(*io, SEEK_END, 0);
		}

		log_object->log_number_incremented = false;
	}

	// Write the contents of the log to the buffer
	WriteRecordToBuffer(buffer, rec);

	// Release the memory of record
	Free(rec);

	return (*io != NULL);
}